import sys
import argparse
import numpy as np

from numpy import *
from math import sqrt


# Input: expects Nx3 matrix of points
# Returns R,t
# R = 3x3 rotation matrix
# t = 3x1 column vector
def read_trajectory(filename, matrix=True):
    """
    Read a trajectory from a text file. 
    
    Input:
    filename -- file to be read
    matrix -- convert poses to 4x4 matrices
    
    Output:
    New data file , based on Input file
    """
    
    file = open(filename)
    data = file.read()
    lines = data.replace(","," ").replace("\t"," ").split("\n") 
    list = [[float(v.strip()) for v in line.split(" ") if v.strip()!=""] for line in lines if len(line)>0 and line[0]!="#"]
    list_ok = []
    for i,l in enumerate(list):
      print l
      #l[2]=l[2]*0.5  # We make a modification on the ground-truth data to get a new dataset based on the ground-truth . In this example field2 = field2*05 . Format of file = timestamp tx ty tz qx qy qz qw
      #list_ok.append(l)
      list_ok.append([ l[1], l[2] , l[3] ]) # take X, Y , Z
    traj = list_ok
    return traj
        
def rigid_transform_3D(A, B):
    assert len(A) == len(B)

    N = A.shape[0]; # total points

    centroid_A = mean(A, axis=0)
    centroid_B = mean(B, axis=0)
    
    # centre the points
    AA = A - tile(centroid_A, (N, 1))
    BB = B - tile(centroid_B, (N, 1))

    print "AA shape";
    print  AA.shape;
    print BB.shape;

    # dot is matrix multiplication for array
    
    H = transpose(AA)* BB

    U, S, Vt = linalg.svd(H)

    R = Vt.T * U.T

    # special reflection case
    if linalg.det(R) < 0:
       print "Reflection detected"
       Vt[2,:] *= -1
       R = Vt.T * U.T

    t = -R*centroid_A.T + centroid_B.T

    print t

    return R, t

# Test with random data

# Random rotation and translation
#R = mat(random.rand(3,3))
#t = mat(random.rand(3,1))

# make R a proper rotation matrix, force orthonormal
#U, S, Vt = linalg.svd(R)
#R = U*Vt

# remove reflection
#if linalg.det(R) < 0:
#   Vt[2,:] *= -1
#   R = U*Vt

# number of points
n = 3000
#n = 4
#A = mat(random.rand(n,3));
#B = R*A.T + tile(t, (1, n))
#B = B.T;

parser = argparse.ArgumentParser(description='''
    This script computes the relative pose error from the ground truth trajectory and the estimated trajectory. 
    ''')
parser.add_argument('orig_file', help='ground-truth trajectory file (format: "timestamp tx ty tz qx qy qz qw")')
parser.add_argument('new_file', help='estimated trajectory file (format: "timestamp tx ty tz qx qy qz qw")')
parser.add_argument('output_file', help='estimated trajectory file (format: "tx ty tz ")')
args = parser.parse_args()
print ("Reading "+args.orig_file)
A = read_trajectory(args.orig_file,False) # reads trajectory from groundTruth and performs small changes
B = read_trajectory(args.new_file,False) # reads trajectory from groundTruth and performs small changes
# recover the transformation
A = np.asmatrix(A)
B = np.asmatrix(B)
print "Points A"
print A
print ""

print "Points B"
print B
print ""

# recover the transformation
ret_R, ret_t = rigid_transform_3D(A, B)

A2 = (ret_R*A.T) + tile(ret_t, (1, n))
A2 = A2.T

# Find the error
err = A2 - B

err = multiply(err, err)
err = sum(err)
rmse = sqrt(err/n);

print "Points A"
print A
print ""

print "Points B"
print B
print ""

print "Points A2"
print A2
print ""

print "Rotation Calculada"
print ret_R
print ""

print "Translation calculada"
print ret_t
print ""

print "RMSE:", rmse
print "If RMSE is near zero, the function is correct!"

#Open a new outputFile, writing mode
fileOutput = open(args.output_file,'w')
listOutput = A2.tolist();
for i,line in enumerate(listOutput):
  #fileOutput.writelines(str(l)+'\n')  # works but it includes brackets and commas
  fileOutput.write('0'+' ')
  for j,field in enumerate(line):
    fileOutput.write(str(field)+' ')
  fileOutput.write('1 2 3 4\n')

  
fileOutput.close()

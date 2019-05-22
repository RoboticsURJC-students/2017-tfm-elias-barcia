all: pdf

pdf: *.tex bibliografia.bib
	pdflatex memoria
	bibtex memoria
	pdflatex memoria

dvi: memoria.tex
	latex memoria.tex	

ps: dvi
	dvips -tlandscape -ta4 -O0cm,0cm -o memoria.ps -ta4 memoria.dvi

clean:
	rm -f *.aux *.log *.lot *.lof *.out *.bbl *.blg *.toc memoria.pdf

release:
	tar -zcvf newrelease.tgz *.tex img/ Makefile named.sty bibliografia.bib named.bst


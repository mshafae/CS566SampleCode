#
# GNU Makefile for the raytracer's grammar
#
# Michael Shafae
# mshafae at fullerton.edu
#
# $Id: Makefile 5893 2015-06-24 20:26:22Z mshafae $
#
#

TARGET = grammar.pdf

SRC = grammar

default all: $(TARGET)

$(TARGET): $(SRC).tex
	pdflatex $(SRC) && pdflatex $(SRC)

clean:
	-rm -f $(SRC).aux $(SRC).log *~

spotless: clean
	-rm -f $(TARGET)

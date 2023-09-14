CURDIR=$(shell pwd)
BINDIR=../../bin


all : xyz2tdm tdmsmooth tdmoffset


xyz2tdm : xyz2tdm.c
	gcc $^ -o $@ 
	@ cd $(BINDIR) && \
	if [ ! -e $@ ]; then \
		ln -s $(CURDIR)/$@ $@ ;\
	fi

tdmsmooth : tdmsmooth.c
	gcc $^ -o $@ 
	@ cd $(BINDIR) && \
	if [ ! -e $@ ]; then \
		ln -s $(CURDIR)/$@ $@ ;\
	fi

tdmoffset : tdmoffset.c
	gcc $^ -o $@ 
	@ cd $(BINDIR) && \
	if [ ! -e $@ ]; then \
		ln -s $(CURDIR)/$@ $@ ;\
	fi


upload : 
	git add -A && \
	git commit -m "Update" && \
	git push -f origin master

fetch :
	git fetch && \
	git merge origin/master

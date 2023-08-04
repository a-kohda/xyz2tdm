xyz2tdm : xyz2tdm.c
	gcc xyz2tdm.c -o xyz2tdm

upload : 
	git add -A && \
	git commit -m "Update" && \
	git push -f origin master

fetch :
	git fetch && \
	git merge origin/master

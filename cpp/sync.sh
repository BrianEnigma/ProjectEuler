#!/bin/sh
rsync -v -r --rsh=ssh --size-only \
	--exclude 'CVS' \
	--exclude '*.sh' \
	--exclude '*.out' \
	* briane@seamus.dreamhost.com:bufferoverrun.org/projecteuler/


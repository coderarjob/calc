help:
	Provide an argument.
evalmake:
	gcc ./common/*.c ./eval/*.c ./stack/*.c -o eval.out

itopmake:
	gcc ./common/*.c ./itop/*.c ./stack/*.c -o itop.out

install:
	mkdir /opt/ocalc-0.0.1a
	cp ./calc ./eval.out ./itop.out /opt/ocalc-0.0.1a/
	cd /opt/ocalc-0.0.1a
	chmod 755 ./calc ./eval.out ./itop.out
	ln ./calc /usr/local/bin/calc
	ln ./itop.out /usr/local/bin/itop.out
	ln ./eval.out /usr/local/bin/eval.out
	cd -
	Installation has completed.
end:
	

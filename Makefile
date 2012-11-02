help:
	Provide an argument.
evalmake:
	gcc ./common/*.c ./eval/*.c ./stack/*.c -o eval.out

itopmake:
	gcc ./common/*.c ./itop/*.c ./stack/*.c -o itop.out

install:
	cp calc eval.out itop.out /usr/local/bin
	Installation has completed.
end:
	

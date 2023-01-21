exec = bs.out #the file that will be executed
sources = $(wildcard src/*.c) #wildcard finds a path
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects) 
	gcc $(objects) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

#this is so you can install the outfile as a command in cmd
install:
	make
	cp ./bs.out /usr/bin/bs

#this is so you can delete your outs and start over
clean: 
	-rm *.out 
	-rm src/*.o
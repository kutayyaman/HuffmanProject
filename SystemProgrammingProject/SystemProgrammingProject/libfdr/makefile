hepsi: derle

derle:
	gcc -I ./libfdr/ -o ./lib/fields.o -c ./libfdr/fields.c	
	gcc -I ./libfdr/ -o ./lib/jrb.o -c ./libfdr/jrb.c
	gcc -I ./libfdr/ -o ./lib/jval.o -c ./libfdr/jval.c
	gcc -I ./libfdr/ -o kripto ./lib/fields.o ./lib/jrb.o ./lib/jval.o ./src/main.c
	
clean:
	rm -f ./lib/*.o 
	rm -f kripto
	
cleanall:
	rm -f .kilit encripted decripted ./*.txt
	make clean

run:
	make clean
	make
	./kripto -e istiklal_marsi.txt encripted
	./kripto -d encripted decripted 

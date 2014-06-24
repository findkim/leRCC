all: leRCC

leRCC: main.o ExtractSigOrf.o ExtractMMSeq.o RunLength.o
	g++ main.o ExtractSigOrf.o ExtractMMSeq.o RunLength.o -o leRCC

main.o: main.cpp
	g++ -c main.cpp

ExtractSigOrf.o: ExtractSigOrf.cpp ExtractSigOrf.h
	g++ -c ExtractSigOrf.cpp

ExtractMMSeq.o: ExtractMMSeq.cpp ExtractMMSeq.h
	g++ -c ExtractMMSeq.cpp

RunLength.o: RunLength.cpp RunLength.h
	g++ -c RunLength.cpp

clean:
	rm -f *.o *.pyc *~ leRCC

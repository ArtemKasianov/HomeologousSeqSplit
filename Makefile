
HomeologousSeqSplit: BaseClasses.o FilesFormats.o sam_mapping_1.o connectioncomponent.o utils.o main_2.o Vertex.o Graph.o Path.o pathespack.o scaffold.o scaffolder.o filteredpathesset.o alternativepathcomparer.o considerpath.o considerscaffold.o usedpathes.o snptextfile.o usedscaffs.o mismatchpointsfile.o
	g++ -o HomeologousSeqSplit BaseClasses.o FilesFormats.o sam_mapping_1.o connectioncomponent.o utils.o main_2.o Vertex.o Graph.o Path.o pathespack.o scaffold.o scaffolder.o filteredpathesset.o alternativepathcomparer.o considerpath.o considerscaffold.o usedpathes.o snptextfile.o usedscaffs.o mismatchpointsfile.o

BaseClasses.o:
	g++ -O -c BaseClasses.cpp
FileFormats.o:
	g++ -O -c FileFormats.cpp
sam_mapping_1.o:
	g++ -O -c sam_mapping_1.cpp
connectioncomponent.o:
	g++ -O -c connectioncomponent.cpp
utils.o:
	g++ -O -c utils.cpp
main_2.o:
	g++ -O -c main_2.cpp
Vertex.o:
	g++ -O -c Vertex.cpp
Graph.o:
	g++ -O -c Graph.cpp
Path.o:
	g++ -O -c Path.cpp
pathespack.o:
	g++ -O -c pathespack.cpp
scaffold.o:
	g++ -O -c scaffold.cpp
scaffolder.o:
	g++ -O -c scaffolder.cpp
filteredpathesset.o:
	g++ -O -c filteredpathesset.cpp
alternativepathcomparer.o:
	g++ -O -c alternativepathcomparer.cpp
considerpath.o:
	g++ -O -c considerpath.cpp
considerscaffold.o:
	g++ -O -c considerscaffold.cpp
usedpathes.o:
	g++ -O -c usedpathes.cpp
snptextfile.o:
	g++ -O -c snptextfile.cpp
usedscaffs.o:
	g++ -O -c usedscaffs.cpp
mismatchpointsfile.o:
	g++ -O -c mismatchpointsfile.cpp

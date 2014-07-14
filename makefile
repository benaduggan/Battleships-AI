#####################################################
# Battleships makefile
#----------------------------------------------------
# INSTRUCTIONS:
#
# Add your own player to the makefile. That means
# (1) Add in both the dependency line and the compile
#     line for the "AITester:" target.
# (2) Specify its dependencies similar to how it is
#     done for thewhiteperl at the bottom of the file.
#
# NOTE: the Linux binaries are exactly that, Linux
# binaries. They are only guaranteed to work on the 
# Linux that we have in the labs and on our servers.
#####################################################

CPPFLAGS = -g -Wall -O2
AITester: main.o BoardV2.o Message.o PlayerV1.o AITester.o \
	CleanPlayer.o OrigGamblerPlayer.o HumanPlayer.o thewhiteperl.o
	g++ $(CPPFLAGS) -o AITester main.o BoardV2.o Message.o PlayerV1.o AITester.o \
	CleanPlayer.o OrigGamblerPlayer.o HumanPlayer.o thewhiteperl.o
	@echo "Executable is 'AITester'"

clean:
	@echo "Removed all .o files. AITester was left -- 'rm' by hand to get rid of it too."
	rm -f *.o

main.o: main.cpp BoardV2.h AITester.h Message.h defines.h PlayerV1.h 
	g++ $(CPPFLAGS) -c main.cpp
	
BoardV2.o: 
	@echo "Getting BoardV2.o from your linuxbinaries.tar"
	tar xvf linuxbinaries.tar BoardV2.o
Message.o: Message.cpp Message.h defines.h
PlayerV1.o: PlayerV1.cpp PlayerV1.h Message.h defines.h
AITester.o: 
	@echo "Getting AITester.o from your linuxbinaries.tar"
	tar xvf linuxbinaries.tar AITester.o
thewhiteperl.o: thewhiteperl.cpp thewhiteperl.h PlayerV1.h Message.h defines.h
CleanPlayer.o: 
	@echo "Getting CleanPlayer.o from your linuxbinaries.tar"
	tar xvf linuxbinaries.tar CleanPlayer.o
OrigGamblerPlayer.o: 
	@echo "Getting OrigGamblerPlayer.o from your linuxbinaries.tar"
	tar xvf linuxbinaries.tar OrigGamblerPlayer.o
HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h PlayerV1.h Message.h defines.h

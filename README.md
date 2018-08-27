# Corewar


This is a group project: __4 people__.


Our team: __opavliuk__, __tkiselev__, __ysamchuk__, __tkuhar__.


Project of __UNIT Factory__ (école 42)


# What is Corewar?

• Corewar is a very peculiar game. It’s about bringing “players” together around a
“virtual machine”, which will load some “champions” who will fight against one another
with the support of “processes”, with the objective being for these champions
to stay “alive”.


• The processes are executed sequentially within the same virtual machine and memory
space. They can therefore, among other things, write and rewrite on top of
each others so to corrupt one another, force the others to execute instructions that
can damage them, try to rewrite on the go the coding equivalent of a Côtes du
Rhône 1982 (that is one delicious French wine!), etc...


• The game ends when all the processes are dead. The winner is the last player
reported to be “alive”.


__Wikipedia ("Core War"):__ https://en.wikipedia.org/wiki/Core_War


# Breakdown of the project’s objectives


This project can be broken down into __three distinctive parts__:


• __The assembler__: this is the program that will compile your champions and translate
them from the language you will write them in (assembly language) into “Bytecode”.Bytecode
is a machine code, which will be directly interpreted by the virtual
machine.


• __The virtual machine__: It’s the “arena” in which your champions will be executed.
It offers various functions, all of which will be useful for the battle of the champions.
Obviously, the virtual machine should allow for numerous simultaneous processes;
we are asking you for a gladiator fight, not a one-man show simulator.


• __The champion__: This one is a special case. Later, in the championship, you will
need to render a super powerful champion, who will scare the staff team to death.
However, rendering this kind of champion is serious work. And since, for now, we
are mostly interested in your capacity to create Corewar’s other programs (i.e. the
assembler and virtual machine), your current champion will only need to prove to
us that you can write bits and pieces of Corewar ASM. This means that the champion
you should render for this project only needs to scare the bejesus out of a
neurasthenic hedgehog.


# Our Bonuses:

__We made some cool bonuses:__


• __Disassembler__: our assembler has flag __'-b'__ which retranslates back your champions from Bytecode into assembly language.


• __Info about champion__: our assember has flag __'-a'__ also, which reads champions assembly file and shows you 
all information about champions (name, comment, commands: opcode, codage, bytes).


• __Network Game Mode__: our corewar has flags __'-s' (server)__ and __'-c' (client)__!
__'-s'__ flag allows you to create a server and other clients (from another computer, on the local network,
which have the IP address of the server), through __'-c'__ flag, can send their best champions and watch the battle on their computers.

# Usages

<br>
<img height="100" width="600" src="https://github.com/lpavliuk/Corewar/blob/master/screenshots/Screen%20Shot%202018-08-13%20at%201.35.53%20PM.png" />
<img height="250" width="600" src="https://github.com/lpavliuk/Corewar/blob/master/screenshots/Screen%20Shot%202018-08-13%20at%201.35.26%20PM.png" />
<br>

# Visualizer

<br>
<img height="600" width="1000" src="https://github.com/lpavliuk/Corewar/blob/master/screenshots/Screen%20Shot%202018-08-13%20at%201.36.54%20PM.png" />
<img height="600" width="1000" src="https://github.com/lpavliuk/Corewar/blob/master/screenshots/Screen%20Shot%202018-08-13%20at%201.37.56%20PM.png" />
<br>

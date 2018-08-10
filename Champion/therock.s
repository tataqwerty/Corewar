# Champion likes banana pancakes with peanut butter and maple syrup!!!
# Work HARD play HARD!!!
#
# Size: 542 bytes
# Created by: opavliuk

.name "The Rock"
.comment "I will kick your ass!"

		add  r8,r8,r8
		zjmp %:start
wall:
		live %1
		fork %:start

########## Wall ###########
wall1: 	live %1
		st   r11, -27
		st   r11, -36
		st   r11, -45
		st   r11, -54
		st   r11, -63
		st   r11, -72
		st   r11, -81
		st   r11, -90
		st   r11, -99
		st   r11, -108
		st   r11, -117
		st   r11, -126
		st   r11, -135
		st   r11, -144
		st   r11, -153
		st   r11, -162
		st   r11, -171
		st   r11, -180
		st   r11, -189
		st   r11, -198
		st   r11, -207
		st   r11, -216
		st   r11, -225
		st   r11, -234
		st   r11, -243
		st   r11, -252
		st   r11, -261
		st   r11, -270
		st   r11, -279
		st   r11, -288
		st   r11, -297
		st   r11, -306
		st   r11, -315
		st   r11, -324
		st   r11, -333
		st   r11, -342
		st   r11, -351
		st   r11, -360
		st   r11, -369
		st   r11, -378
		st   r11, -387
		st   r11, -396
		st   r11, -405
		st   r11, -414
		st   r11, -423
		st   r11, -432
		st   r11, -441
		st   r11, -450
		st   r11, -459
		st   r11, -468
		st   r11, -477
		st   r11, -486
		st   r11, -495

		add  r8,r8,r8
		zjmp  %:wall1

#############################
start:
		ld %0,r11
		sti r1,%:l2,%1
		sti r1,%0,%8

	    live %1

l2:
		live %1
		sti r1,%:for2,%1
		sti r1,%:for1,%1
		sti r1,%:f,%1

		fork %:wall

########## Copy process on 4 processes ##########
f:	
		live %1
		sti r1,%:jump,%1
		fork %:for2

####### 1,2 processes ########
for1:
		live %1
		sti r1,%:write1,%1
		sti r1,%:write2,%1
		fork %:write2

write1:		
		live %1
		ld   %321, r14	
		ldi  %0, %:jump, r15

		and r8,%0,r8
		zjmp %:jump

write2: 
		live %1
		ld   %325, r14	
		ldi  %4, %:jump, r15

		and r8,%0,r8
		zjmp %:jump

####### 3,4 processes ########
for2:
		live %1
		sti r1,%:write3,%1
		sti r1,%:write4,%1
		fork %:write4

write3: 
		live %1
		ld   %329, r14	
		ldi  %8, %:jump, r15
		
		and r8,%0,r8
		zjmp %:jump

write4: 
		live %1
		ld   %333, r14	
		ldi  %12, %:jump, r15
		
		and r8,%0,r8
		zjmp %:jump

######### All 4 processes is jumping together ######
jump:
		live %1
		sti  r15,%0,r14
		zjmp %315

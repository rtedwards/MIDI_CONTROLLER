import sys, pygame, pygame.midi
 
# set up pygame
pygame.init()
pygame.midi.init()
 
# list all midi devices
for x in range( 0, pygame.midi.get_count() ):
	print pygame.midi.get_device_info(x)
 
# open a specific midi device
#inp = pygame.midi.Input(2)
if device_id is None:
    input_id = pygame.midi.get_default_input_id()
else:
    input_id = device_id

print ("using input_id :%s:" % input_id)
i = pygame.midi.Input( input_id )

pygame.display.set_mode((1,1))

# run the event loop
while True:
	if inp.poll():
		# no way to find number of messages in queue
		# so we just specify a high max value
		print inp.read(1000)
 
	# wait 10ms - this is arbitrary, but wait(0) still resulted
	# in 100% cpu utilization
	pygame.time.wait(10)
# C source files
PROJECT_EXPERIMENTS   	=	experiments/experiment_steer_left.c     		\
				  			experiments/experiment_steer_right.c			\
				  		
				  
PROJECT_CSRC 	= src/main.c src/Control.c src/SteerAngle.c src/serial.c	\
					$(PROJECT_EXPERIMENTS)
# C++ source files

PROJECT_CPPSRC 	= 
# Directories to search headers in

PROJECT_INCDIR	= include													\
# Additional libraries

PROJECT_LIBS	=
# Compiler options

PROJECT_OPT     =

# Additional .mk files are included here

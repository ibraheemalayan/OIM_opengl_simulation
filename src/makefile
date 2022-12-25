.DEFAULT_GOAL := run_cli

# use the rest as arguments for "run"
RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
# ...and turn them into do-nothing targets
$(eval $(RUN_ARGS):;@:)

PWD := $(shell pwd)

# Standalone GUI
compile_gui:
	@echo "Compiling..."
	gcc ui/ui.c -lGL -lGLU -lglut -lm -o bin/standalone_gui.o


run_gui: compile_gui;
	@echo "Running GUI..."
	$(shell export DISPLAY=:0)
	./bin/standalone_gui.o

# Debug Standalone GUI
compile_gui_debug:
	@echo "Compiling..."
	gcc ui/ui.c -g -lGL -lGLU -lglut -lm -o bin/standalone_gui.o


debug_gui: compile_gui_debug;
	@echo "Running GUI..."
	$(shell export DISPLAY=:0)
	gdb ./bin/standalone_gui.o

#	StandAlone CLI
compile_cli:
	@echo "Compiling..."
	gcc -pthread cli/main.c -o bin/main.o
	gcc -pthread cli/child.c -o bin/child.o
#	gcc cli/standalone_child.c -lm -o bin/standalone_child.o


run_cli: compile_cli;
	@echo "Running CLI..."
	./bin/main.o $(RUN_ARGS)

# # Debug StandAlone CLI
# debug_compile_cli:
# 	@echo "Compiling CLI with -g ..."
# 	gcc cli/standalone_parent.c -lm -g -o bin/standalone_parent.o
# 	gcc cli/standalone_child.c -lm -g -o bin/standalone_child.o

# debug_cli: debug_compile_cli;
# 	@echo "Running GDB..."
# 	gdb --args ./bin/standalone_parent $(RUN_ARGS)

# # Compile all
# compile:
# 	@echo "Compiling..."
# 	gcc ui/attached_ui.c -lGL -lGLU -lglut -lm -o bin/attached_gui.o
# 	gcc cli/attached_parent.c -lm -o bin/attached_parent.o
# 	gcc cli/attached_child.c -lm -o bin/attached_child.o

# run: compile;
# 	@echo "Running..."
# 	$(shell export DISPLAY=:0)
# 	./bin/attached_parent.o $(RUN_ARGS)


# # Compile all
# compile_debug_all:
# 	@echo "Compiling for debug..."
# 	gcc ui/attached_ui.c -lGL -lGLU -g -lglut -lm -o bin/attached_gui.o
# 	gcc cli/attached_parent.c -lm -g -o bin/attached_parent.o
# 	gcc cli/attached_child.c -lm -g -o bin/attached_child.o

# debug: compile_debug_all;
# 	@echo "Debugging All..."
# 	$(shell export DISPLAY=:0)
# 	gdb --args ./bin/attached_parent.o $(RUN_ARGS)
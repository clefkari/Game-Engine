glfw3_dep = dependency('glfw3')
glew_dep = dependency('glew')

sources = ['engine.cpp']

if (host_machine.system() == 'darwin')
    engine_exe = executable('engine',
        include_directories: include,
 		sources : sources,
		dependencies : [glfw3_dep, glew_dep, dependency('appleframeworks',
			modules: ['OpenGL', 'Cocoa', 'IOKit', 'CoreVideo'])])

elif (host_machine.system() == 'linux')
    engine_exe = executable('engine', 
        include_directories: include,
		sources : sources, 
		dependencies : [glfw3_dep, glew_dep])
endif

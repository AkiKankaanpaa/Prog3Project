TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
	Game \
	Tests

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib

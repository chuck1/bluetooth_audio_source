src=$(shell find graph/ -regex ".*\.dot")
dst=$(patsubst %.dot,%.svg,$(src))

%.svg: %.dot
	dot -Tsvg -o$@ $^

all: $(dst)
	@echo $(src)
	@echo $(dst)
	



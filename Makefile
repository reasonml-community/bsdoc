NODE_BIN=./node_modules/.bin
BSB=$(NODE_BIN)/bsb

.PHONY: deps
deps:
	@yarn

.PHONY: docs
docs: build
	@./bin/bsdoc.js build --verbose BsDoc

.PHONY: build
build: deps
	@$(BSB) -make-world

.PHONY: world
world: deps
	@$(BSB) -make-world -w

.PHONY: fmt
fmt: deps
	@$(NODE_BIN)/bsrefmt --in-place ./src/*.re

.PHONY: clean
clean:
	@$(BSB) -clean-world

.PHONY: cleanall
cleanall: clean
	@rm -rf node_modules lib

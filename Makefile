NODE_BIN=./node_modules/.bin
BSB=$(NODE_BIN)/bsb

.PHONY: deps
deps:
	@yarn

.PHONY: docs
docs: build
	@./scripts/mk-docs.sh ReActor ./lib/bs/src ./src "*.cmti"
	@./scripts/mk-docs.sh Examples ./lib/bs/examples ./examples "*.cmt"

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

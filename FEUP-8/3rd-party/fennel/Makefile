fennel.h: fennel.lua
	xxd -i $^ > $@

# This is simpler than hacking package.searchers for one file.
fennel.lua: fennel_original.lua
	sed "s/return module/package.loaded['fennel'] = module/" $^ > $@

# Assuming you have a checkout as a sibling dir to this repo.
fennel_original.lua:
	cp ../../fennel/fennel.lua $@

update: fennel_original.lua

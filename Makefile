
avalanche: avalanche.c avalanche.h param.h main.c
	cc -o $@ avalanche.c main.c

param.h: config
	./$^ >$@

config: config.c config.h
	cc -o $@ config.c

avalanche.ff: avalanche
	./$^ > $@

avalanche.png: avalanche.ff
	ff2png <$^ >$@


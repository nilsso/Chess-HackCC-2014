MKDIR_P = mkdir -p
RM = rm -rf

OUTDIR = out

target = chess.out

.PHONY: directories clean remove

directories:
	$(MKDIR_P) $(OUTDIR)

clean:
	$(RM) $(OUTDIR)

remove:
	$(clean)
	$(RM) ${target}


CC = gcc
SRCDIR = src
OBJDIR = obj
INCLDIR = incl
PRCSDIR = prcs
SISTEMA := -D LINUX
CLEAN_COMMAND := rm -f
EJECUTABLEMAIN = lab2
EJECUTABLELECTURA = mainLectura
EJECUTABLECONVERSION = mainGrises
EJECUTABLEFILTRO = mainFiltro
EJECUTABLEBINARIZACION = mainBinarizacion
EJECUTABLECLASIFICACION = mainClasificacion
EJECUTABLEESCRITURA = mainEscritura



all: clean main lectura escalaGrises filtroRealce binarizacion clasificacion escritura
	$(eval LOCAL=true)
	@echo "-------------------------------------------------------"
	@echo "Ejecutable generado! Nombre: $(EJECUTABLEMAIN) "

main: $(OBJDIR)/main.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable main ..."
	  ($(CC) $^ -o $(EJECUTABLEMAIN) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )
	  @echo "-------------------------------------------------------"

lectura: $(OBJDIR)/mainLectura.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable $(EJECUTABLELECTURA) ..."
	  ($(CC) $^ -o $(EJECUTABLELECTURA) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

conversion: $(OBJDIR)/mainGrises.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable $(EJECUTABLECONVERSION) ..."
	  ($(CC) $^ -o $(EJECUTABLECONVERSION) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

filtro: $(OBJDIR)/mainFiltro.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable $(EJECUTABLEFILTRO) ..."
	  ($(CC) $^ -o $(EJECUTABLEFILTRO) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

binarizacion: $(OBJDIR)/mainBinarizacion.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable $(EJECUTABLEBINARIZACION) ..."
	  ($(CC) $^ -o $(EJECUTABLEBINARIZACION) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

clasificacion: $(OBJDIR)/mainClasificacion.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable $(EJECUTABLECLASIFICACION) ..."
	  ($(CC) $^ -o $(EJECUTABLECLASIFICACION) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

escritura: $(OBJDIR)/mainEscritura.o $(OBJDIR)/lectura.o $(OBJDIR)/filtroRealce.o $(OBJDIR)/escritura.o \
	  $(OBJDIR)/escalaGrises.o $(OBJDIR)/clasificacion.o $(OBJDIR)/binarizacion.o
	  $(eval LOCAL=true)
	  @echo "Generando ejecutable $(EJECUTABLEESCRITURA) ..."
	  ($(CC) $^ -o $(EJECUTABLEESCRITURA) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

$(OBJDIR)/main.o: $(SRCDIR)/main.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/lectura.o: $(SRCDIR)/lectura.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/filtroRealce.o: $(SRCDIR)/filtroRealce.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/escritura.o: $(SRCDIR)/escritura.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/escalaGrises.o: $(SRCDIR)/escalaGrises.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/clasificacion.o: $(SRCDIR)/clasificacion.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/binarizacion.o: $(SRCDIR)/binarizacion.c
				@echo "Generando archivos object de $@ ...."
				($(CC) -c $< -o $@ && echo "[OK]") \
				||  (echo "[ERROR]" && exit 1; )
				$(eval LOCAL=true)

$(OBJDIR)/mainLectura.o: $(PRCSDIR)/mainLectura.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/mainGrises.o: $(PRCSDIR)/mainGrises.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/mainFiltro.o: $(PRCSDIR)/mainFiltro.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/mainBinarizacion.o: $(PRCSDIR)/mainBinarizacion.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/mainClasificacion.o: $(PRCSDIR)/mainClasificacion.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

$(OBJDIR)/mainEscritura.o: $(PRCSDIR)/mainEscritura.c
				@echo "Generando archivos object de $@ ...."
				$(CC) -c $< -o $@ 

clean:
	$(eval LOCAL=true)
	@echo "Eliminando .out antiguos..."
	@echo >> rm.out
	$(eval LOCAL=true)
	(($(CLEAN_COMMAND) *.out || $(CLEAN_COMMAND_v2) *.out || $(CLEAN_COMMAND_v3) *.out ) \
		&& echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

	@echo "Eliminando .o antiguos..."
	(cd $(OBJDIR) && echo >> rm.o )


	(cd $(OBJDIR) && ($(CLEAN_COMMAND) *.o || $(CLEAN_COMMAND_v2) *.o ) \
		&& echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; ) \


	@echo "Limpieza de archivos antiguos completa!!"
	@echo "-------------------------------------------------------"

.SILENT: clean make all main lectura conversion filtro binarizacion clasificacion escritura $(OBJDIR)/*.o\
		$(SRCDIR)/%.c $(PRCSDIR)/%.c 
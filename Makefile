PARTICLE = particle
DEVICE_TYPE = photon
DEVICE_NAME ?= my_photon

compile:
	$(PARTICLE) compile $(DEVICE_TYPE)

flash: compile
	$(PARTICLE) flash $(DEVICE_NAME)

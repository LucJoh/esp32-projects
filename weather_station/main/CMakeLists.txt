idf_component_register(
    SRCS "weather_station.c"
    INCLUDE_DIRS "."
    REQUIRES dht
    REQUIRES max7219
)

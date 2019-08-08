INCLUDES=-I/usr/local/include -I.. -I. -I../../../include
CFLAGS = $(INCLUDES) -std=c++17 # -O2 or -g
#LIBS = -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lrt
WEBSOCKET_LIBS =  -lpthread -lcrypto -lssl -lrt
SRCS = wsapi.cpp
HDRS = wsapi.hpp

bitstamp: bitstamp.cpp $(SRCS) $(HDRS)
	g++ $(CFLAGS) $@.cpp $(LIBS) $(WEBSOCKET_LIBS) -o $@

simple_example: simple_example.cpp $(SRCS) $(HDRS)
	g++ $(CFLAGS) $@.cpp $(SRCS) $(LIBS) $(WEBSOCKET_LIBS) -o $@

async_ssl_bitstamp_allsteps: async_ssl_bitstamp_allsteps.cpp
	g++ $(CFLAGS) $@.cpp $(LIBS) $(WEBSOCKET_LIBS) -o $@


clean:
	rm -f simple_example
	rm -f bitstamp
	rm -f async_ssl_bitstamp_allsteps





import datetime
import numpy as np
import json
import sys


class datetime_utils:
    EPOCH = datetime.datetime(1970,1,1)
    DAY   = datetime.timedelta(days=1)
    SEC   = datetime.timedelta(seconds=1)
    US    = datetime.timedelta(microseconds=1)
    FMT0  = "%Y%m%d"
    FMT1  = "%m-%d-%Y %H:%M:%S"
    FMT2  = "%Y-%m-%d"
    FMT3  = "%m-%d-%Y"
    FMT4  = "%Y-%m-%dT%H:%M:%S.%fZ"
    
    # convert format string to datetime
    def str2dt(dtstr, fmt="%Y-%m-%dT%H:%M:%S.%fZ"):
        return datetime.datetime.strptime(dtstr, fmt)

    # convert datetime to days from Epoch
    def daysfrom(dt):
        return (dt - datetime_utils.EPOCH)/datetime_utils.DAY

    # convert datetime to seconds from Epoch
    def secfrom(dt):
        return (dt - datetime_utils.EPOCH)/datetime_utils.SEC

    # convert datetime to microseconds from Epoch
    def usfrom(dt):
        return (dt - datetime_utils.EPOCH)/datetime_utils.US

    # convert microseconds from Epoch to datetime
    def us2dt(us):
        return datetime_utils.EPOCH + datetime.timedelta(microseconds=us)

    # convert seconds from Epoch back to datetime
    def fromtimestamp(ts):
        return datetime.datetime.utcfromtimestamp(ts)
    
class time_utils:
    EPOCH = np.datetime64('1970-01-01T00:00:00')
    SEC   = np.timedelta64(1, 's')
    US    = np.timedelta64(1, 'us')
    NS    = np.timedelta64(1, 'ns')
    
    
    # convert datestring in format below to np.datetime64
    def str2np64(dstr) :
        # "2019-07-16T00:43:07.684919"
        dstr = dstr.replace("Z","")
        return np.datetime64(dstr)

    # convert python datetime to np.datetime64
    def tonp64(dt):
        return np.datetime64(dt)

    # seconds from Epoch, rannge +/- 2.9e11 years
    def secfrom(np64):
        return (np64 - time_utils.EPOCH)/time_utils.SEC

    # microseconds from Epoch, range +/- 2.9e5 years
    def usfrom(np64):
        return (np64 - time_utils.EPOCH)/time_utils.US

    # nanoseconds from Epoch, range +/- 292 years, max=2262 AD
    def nsfrom(np64):
        return (np64 - time_utils.EPOCH)/time_utils.NS

    # get start of day
    def midnight(np64):
        sec=time_utils.secfrom(np64)
        dt= datetime_utils.fromtimestamp(sec)
        return np.datetime64(datetime.datetime(dt.year, dt.month, dt.day))
        
    # nanoseconds from start of Day
    def nsfrommidnight(np64):
        return (np64 - time_utils.midnight(np64))/time_utils.NS

                

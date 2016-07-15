# HDEEM examples

## hdeem timestats

usage:

    startHdeem # part of official bull hdeem
    # Run your application and get timestamps of core phase etc.
    # Should not run for more than 8 hours
    ./hdeem_timestats start_time end_time
    # you do not need to run stopHdeem.

Both timestamps shall be in unix epoch milliseconds.

The program will provide the following information for each hdeem sensor with respect to the time interval.

sensor (name)
avg (average power in W)
min (minmal power in W)
max (maximum power in W)
energy (consumed enrgy in J)
total samples (for the duration betwen startHdeem and stopHdeem)
interval samples (samples within in the requsted interval)
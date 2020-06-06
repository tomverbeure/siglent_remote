
# Introduction

My Siglent SDS2304X oscilloscope is a relatively pricy piece of equipment, $2000. I justified its purchase with the classic "this will
be the last oscilliscope that I'll ever buy."

It's a very decent scope, but the GUI is clunky at time. And once you start messing around with cursors or with moving the
zoom window, things slow down to a crawl.

So when I learned about glscopeclient, an ambitious project by Andrew Zonenberg, I was immediately interested. glscopeclient reduces
your oscilloscope to just a dumb data acquisition device and moves all the smarts to your PC. It can do all kinds of advance
signal analysis, protocol decoding etc. And it has been designed with speed in mind.

glscopeclient (or, better, the underlying `scopehal` API) already had some very basic Siglent oscilloscope support, but it just didn't
work on mine: there was no VXI-11 support or USBTMC support (the only supported protocols on my slightly older scope), and even after
that, there were major issues with processing the incoming data.

The biggest issues have been fixed now. 

One of the biggest outcomes of that whole exercise was the realization that the Siglent scope is really bad at real-time remote
data acquisition: you'd thing 


The past few weeks, I've spent what little free time that remaining on making it work my Siglent scope.


// blackrain - sample based scheduling
// 2008

+NetAddr {
	sendPosBundle { arg position ... args; // a 64 bit (double) position value
		_NetAddr_SendPosBundle
		^this.primitiveFailed;
	}
}

+Server {	
	sendPosBundle { arg position ... msgs;
		addr.sendPosBundle(position, *msgs)
	}
 	
 	listSendPosBundle { arg position, msgs;
		addr.sendPosBundle(position, *msgs)
	}
	
	halPosition { arg position; ^position + this.sampleStartTime }
	
	getSampleStartTime { arg doneAction;
		var resp;
		resp = OSCresponderNode(addr, '/sampleStartTime', { arg t, r, m, a;
			sampleStartTime = m[1];
			r.remove;
			doneAction.value(this);
		}).add;
		SystemClock.sched(0.5, { resp.remove; nil });
		
		this.sendMsg("sampleStartTime");
	}
}

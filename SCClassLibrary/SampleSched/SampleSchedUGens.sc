
// blackrain dot sc at gmail dot com - 2008

SpawnBlock	: InfoUGenBase {}	// ir
SpawnOffset	: InfoUGenBase {}	// ir

BlockCount	: UGen {
	*kr {
		^this.multiNew('control')
	}
}

BlockOffset	: UGen {
	*ar {
		^this.multiNew('audio')
	}
}

OneImpulse	: UGen {
	*ar { arg phase = 0.0;
		^this.multiNew('audio', phase)
	}
}

ImpulseDriver : UGen {
	*ar { arg samples = 44100;
		^this.multiNew('audio', samples)
	}
}


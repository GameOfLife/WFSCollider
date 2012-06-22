// this method was modified to create relative symlinks to the quark files, 
// so moving the app doesn't affect the file references

+ Quarks {
	install { | name , includeDependencies=true, checkoutIfNeeded=true |
		var q, deps, installed, dirname, quarksForDep;

		if(this.isInstalled(name),{
			(name + "already installed").inform;
			^this
		});

		q = local.findQuark(name);
		if(q.isNil,{
			if(checkoutIfNeeded) {
				(name.asString + " not found in local quarks; checking out from remote ...").postln;
				this.checkout(name, sync: true);
				q = local.reread.findQuark(name);
				if(q.isNil, {
					Error("Quark" + name + "install: checkout failed.").throw;
				});
			}
			{
				Error(name.asString + "not found in local quarks.  Not yet downloaded from the repository ?").throw;
			};
		});

		if(q.isCompatible.not,{
			(q.name + " reports that it is not compatible with your current class library.  See the help file for further information.").inform;
			^this
		});

		// create /quarks/ directory if needed
		if(this.repos.checkDir.not){this.checkoutDirectory};

		// Now ensure that the dependencies are installed (if available given the current active reposses)
		if(includeDependencies, {
			q.dependencies(true).do({ |dep|
				quarksForDep = if(dep.repos.isNil, {this}, {Quarks.forUrl(dep.repos)});
				if(quarksForDep.isNil, {
					("Quarks:install - unable to find repository for dependency '" ++ dep.name
						++ "' - you may need to satisfy this dependency manually. No repository detected locally with URL "++dep.repos).warn;
				}, {
					if(quarksForDep.isInstalled(dep.name).not, {
						try({
							quarksForDep.install(dep.name, false, checkoutIfNeeded)
						}, {
							("Unable to satisfy dependency of '"++name++"' on '"++dep.name
								++"' - you may need to install '"++dep.name++"' manually.").warn;
						});
					});
				});
			});
		});

		// Ensure the correct folder-hierarchy exists first
		dirname = (Platform.userExtensionDir +/+  local.name +/+ q.path).dirname;
		if(File.exists(dirname).not, {
			("mkdir -p " + dirname.escapeChar($ )).systemCmd;
		});

		// install via symlink to Extensions/<quarks-dir>
		
		// MODIFIED FOR STANDALONE: create relative link
		
		("ln -s " + ("../../../quarks" +/+ q.path).escapeChar($ ) + 
			(Platform.userExtensionDir +/+ local.name +/+ q.path).escapeChar($ )).systemCmd;
		
		/*
		("ln -s " + ("../../quarks" +/+ q.path).escapeChar($ ) + 
			(String.scDir +/+ "Help" +/+ local.name +/+ q.path).escapeChar($ )).systemCmd;
		*/
		
		// end mod
		(q.name + "installed").inform;
	}
	
}
#Pokevis

Stream visualizer for Nuzlocke runs of the Gen 4 and Gen 5 Pokémon games.

This was created to serve as a visual aid for people watching Pokémon livestreams (specifically Nuzlockes), but without use of Lua scripting, to give the user more control.  It is, however, still in testing.

##Features

###Pokémon Data Logger

Keeps track of every Pokémon you catch.  The terminal window allows you to enter the things that happen to your Pokémon.

* Catching: `[species] caught`
  * What level? `[#]`
  * What did you nickname it? `[nickname]`
* Leveling up: `[nickname] dinged`
* Evolution: `[nickname] evolved into [species]`
* Death: `[nickname] died`
  * To what did [nickname] die? `[reason]`
* Deposit: `[nickname] deposited`
* Withdraw: `[nickname] withdrawn`
* Egg get: `Egg obtained`
* Egg hatch: `Egg hatched`
  * What hatched from the egg? `[species]`
  * What did you nickname it? `[nickname]`

###Pokémon Party Display

Shows the status of each member of your party.  This will show as a banner across the top of your screen.

* Sprite
* Nickname
* Level
* Color change upon death

###Event display

With each console command, the event log, which is on the right side of the window, updates, showing what happens moment-to-moment.  Each event is timestamped, so that your viewers can see how things are coming along.

In addition to the console commands for the Data Logger, there is also a milestone victory command: `[person/legendary] defeated`.  While this, of course, doesn't affect the Party Display, I do feel it is important to show these kinds of victories.

The Event Display provides room for a 600 x 165 logo, which you can customize by replacing Logo.png.

###Data Save and Load

You didn't expect to have to do an entire game in one sitting, did you?  Of course not, and you should never have to leave Pokevis running.  With the `exit` command, not only are you closing Pokevis, but you are also saving your Party, the Pokémon in your PC, and every event that has been logged.  This all goes into the cleverly named "save.txt".  So, when you next load Pokevis, everything will show up automagically.  Even the Event Display is right back where it was, with the addition of the "Session ended" event from the previous session and a new "Game resumed" event created when you start Pokevis.

But what if you want to do more than one run?  Perhaps you want to save your old memories or want to spice things up by having multiple runs going?  All you have to do is rename the old run's save file to something other than "save.txt", and Pokevis will start a new run's save file for you.

Choosing a save file may be implemented in a future version.

**Important:** Unless you want to lose data, do not click the close button on the console.  That will end Pokevis right where it is, and thus not give it the opportunity to save your data.

###Customizable background

Pokevis reads in a 1920 x 1080 PNG (Bkg.png) that serves as the background for the two displays and the game itself.  The provided background leaves space for the game to be chromakeyed in via OBS.  However, this functionality is not yet available in OBS (coming in the rewrite), so Border.png must be separately laid over in the meantime.

The chromakey color is 0x00ff00.  No sprites on the given spritesheet contain this value.  Please be aware of this when designing your backgrounds, borders, and logos.

##Features Pokevis does not have
* Support for Gen 6
  * A sprite sheet with Gen 6 Pokémon is hard to come by.  Also, the 3DS screen size kind of ruins the design.
* Support for Gens 1-3
  * Egg hatch level is hard-coded right now.  Also, the GBA and GB screen size ruins the design a bit.
* Support for non-Nuzlocke runs
  * There is no `revive` command.
* Interface with DeSmuME for automatic logging
  * That'd be a little much for me to try.  I know it's possible, given Twitch Plays Pokémon, but that'd be quite the undertaking.
* Changing nicknames
  * Didn't bother.  Might put that in later.
* In-program selection of save files
  * Didn't bother.  Might put that in later.
* Support for any Pokémon spritesheet other than the one with which it comes
  * Another instance of hardcoding.  It'd be a lot of work to give better support.
* Support for genders
  * Not super important to me due to the following item
* Support for alternate forms
  * Hand-coding the rules for alternate forms does not sound like my idea of fun.
* Rules on evolution (any Pokémon can evolve into any other at any time; you are responsible for keeping things accurate)
  * Hand-coding the rules for evolution does not sound like my idea of fun.
* Support for platforms other than 64-bit Windows
  * OBS only really works on Windows at this point.  Excluding 32-bit is my way of sticking it to people falling behind.
* Saving when hitting the close button instead of typing the `exit` command
  * Don't know how to fix this.  May research it.
* Support for any monitor resolution lower than 1920 x 1080
  * Party display can be illegible when streamed to smaller displays, and the Party display is designed to take the 96 x 96 sprite size into account.
* Customizable text (font/color)
  * I mean, you can go ahead and put your own font in the folder and rename the file "consola" if you want, but I built Pokevis with a single-width font in mind.  Maybe it's because I'm a programmer, but I like single-width fonts.  Expecially Consolas.
* Support for separation of the Party and Event Displays in Open Broadcaster Software.
  * OBS also does not like accepting two separate captures from the same game, which is what OBS treats SMFL windows as.
* Support for daycare
  * Not using it for my Nuzlocke.  May implement if there is demand.  Super simple, just didn't feel like it.

##Final thoughts

Pokevis was built using SFML, a multimedia library which can be found at http://sfml-dev.org.  SFML is the copyright of Laurent Gomila.  Pokevis was inspired by Lithiarch, who pressured me into doing a Nuzlocke in the first place.  My Nuzlocke of Black 2 can be found at http://twitch.tv/pixley once that starts happening.

I'll post a ZIP file for the Pokevis executable when I'm done testing it.

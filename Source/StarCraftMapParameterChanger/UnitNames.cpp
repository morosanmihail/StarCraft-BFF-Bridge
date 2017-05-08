#include "UnitNames.h"

void IgnoreErr(const char* file, unsigned int line, const char* msg, ...)
{

}

const char* DefaultUnitDisplayName[233] =
{
	/*  0*/ "Terran Marine", //Change
	/*  1*/ "Terran Ghost", //Change
	/*  2*/ "Terran Vulture", //Change
	/*  3*/ "Terran Goliath", //Change
	/*  4*/ "Goliath Turret",
	/*  5*/ "Terran Siege Tank (Tank Mode)", //Change
	/*  6*/ "Tank Turret type 1",
	/*  7*/ "Terran SCV", //Change
	/*  8*/ "Terran Wraith", //Change
	/*  9*/ "Terran Science Vessel",
	/* 10*/ "Gui Montag (Firebat)",
	/* 11*/ "Terran Dropship",
	/* 12*/ "Terran Battlecruiser", //Change
	/* 13*/ "Vulture Spider Mine",
	/* 14*/ "Nuclear Missile",
	/* 15*/ "Terran Civilian",
	/* 16*/ "Sarah Kerrigan (Ghost)",
	/* 17*/ "Alan Schezar (Goliath)",
	/* 18*/ "Alan Schezar Turret",
	/* 19*/ "Jim Raynor (Vulture)",
	/* 20*/ "Jim Raynor (Marine)",
	/* 21*/ "Tom Kazansky (Wraith)",
	/* 22*/ "Magellan (Science Vessel)",
	/* 23*/ "Edmund Duke (Tank Mode)",
	/* 24*/ "Edmund Duke Turret (Tank Mode)",
	/* 25*/ "Edmund Duke (Siege Tank)",
	/* 26*/ "Edmund Duke Turret (Siege Mode)",
	/* 27*/ "Arcturus Mengsk (Battlecruiser)",
	/* 28*/ "Hyperion (Battlecruiser)",
	/* 29*/ "Norad II (Battlecruiser)",
	/* 30*/ "Terran Siege Tank (Siege Mode)",
	/* 31*/ "Tank Turret type 2",
	/* 32*/ "Terran Firebat", //Change
	/* 33*/ "Scanner Sweep",
	/* 34*/ "Terran Medic", //Change
	/* 35*/ "Zerg Larva",
	/* 36*/ "Zerg Egg",
	/* 37*/ "Zerg Zergling", //Change
	/* 38*/ "Zerg Hydralisk", //Change
	/* 39*/ "Zerg Ultralisk", //Change
	/* 40*/ "Zerg Broodling", //Change
	/* 41*/ "Zerg Drone", //Change
	/* 42*/ "Zerg Overlord", //Change
	/* 43*/ "Zerg Mutalisk", //Change
	/* 44*/ "Zerg Guardian", //Change
	/* 45*/ "Zerg Queen", //Change
	/* 46*/ "Zerg Defiler", //Change
	/* 47*/ "Zerg Scourge", //Change
	/* 48*/ "Torrasque (Ultralisk)",
	/* 49*/ "Matriarch (Queen)",
	/* 50*/ "Infested Terran",
	/* 51*/ "Infested Kerrigan (Infested Terran)",
	/* 52*/ "Unclean One (Defiler)",
	/* 53*/ "Hunter Killer (Hydralisk)",
	/* 54*/ "Devouring One (Zergling)",
	/* 55*/ "Kukulza (Mutalisk)",
	/* 56*/ "Kukulza (Guardian)",
	/* 57*/ "Yggdrasill (Overlord)",
	/* 58*/ "Terran Valkyrie", //Change
	/* 59*/ "Mutalisk Cocoon", //Change
	/* 60*/ "Protoss Corsair", //Change
	/* 61*/ "Protoss Dark Templar (Unit)", //Change
	/* 62*/ "Zerg Devourer", //Change
	/* 63*/ "Protoss Dark Archon", //Change
	/* 64*/ "Protoss Probe", //Change
	/* 65*/ "Protoss Zealot", //Change
	/* 66*/ "Protoss Dragoon", //Change
	/* 67*/ "Protoss High Templar", //Change
	/* 68*/ "Protoss Archon", //Change
	/* 69*/ "Protoss Shuttle",
	/* 70*/ "Protoss Scout",
	/* 71*/ "Protoss Arbiter", //Change
	/* 72*/ "Protoss Carrier", //Change
	/* 73*/ "Protoss Interceptor", //Change
	/* 74*/ "Protoss Dark Templar (Hero)",
	/* 75*/ "Zertual (Dark Templar)",
	/* 76*/ "Tassadar/Zeratul (Archon)",
	/* 77*/ "Fenix (Zealot)",
	/* 78*/ "Fenix (Dragoon)",
	/* 79*/ "Tassadar (Templar)",
	/* 80*/ "Mojo (Scout)",
	/* 81*/ "Warbringer (Reaver)",
	/* 82*/ "Gantrithor (Carrier)",
	/* 83*/ "Protoss Reaver", //Change
	/* 84*/ "Protoss Observer",
	/* 85*/ "Protoss Scarab", //Change
	/* 86*/ "Danimoth (Arbiter)",
	/* 87*/ "Aldaris (Templar)",
	/* 88*/ "Artanis (Scout)",
	/* 89*/ "Rhynadon (Badlands)",
	/* 90*/ "Bengalaas (Jungle Critter)",
	/* 91*/ "Unused type 1",
	/* 92*/ "Unused type 2",
	/* 93*/ "Scantid (Desert)",
	/* 94*/ "Kakaru (Twilight)",
	/* 95*/ "Ragnasaur (Ash World)",
	/* 96*/ "Ursadon (Ice World)",
	/* 97*/ "Zerg Lurker Egg",
	/* 98*/ "Raszagal (Dark Templar)",
	/* 99*/ "Samir Duran (Ghost)",
	/*100*/ "Alexei Stukov (Ghost)",
	/*101*/ "Map Revealer",
	/*102*/ "Gerard DuGalle (Ghost)",
	/*103*/ "Zerg Lurker", //Change
	/*104*/ "Infested Duran (Infested Terran)",
	/*105*/ "Disruption Web",
	/*106*/ "Terran Command Center",
	/*107*/ "Terran Comsat Station",
	/*108*/ "Terran Nuclear Silo",
	/*109*/ "Terran Supply Depot",
	/*110*/ "Terran Refinery",
	/*111*/ "Terran Barracks",
	/*112*/ "Terran Academy",
	/*113*/ "Terran Factory",
	/*114*/ "Terran Starport",
	/*115*/ "Terran Control Tower",
	/*116*/ "Terran Science Facility",
	/*117*/ "Terran Covert Ops",
	/*118*/ "Terran Physics Lab",
	/*119*/ "Unused Terran Bldg type 1",
	/*120*/ "Terran Machine Shop",
	/*121*/ "Unused Terran Bldg type 2",
	/*122*/ "Terran Engineering Bay",
	/*123*/ "Terran Armory",
	/*124*/ "Terran Missile Turret",
	/*125*/ "Terran Bunker",
	/*126*/ "Norad II (Crashed Battlecruiser)",
	/*127*/ "Ion Cannon",
	/*128*/ "Uraj Crystal",
	/*129*/ "Khalis Crystal",
	/*130*/ "Infested Command Center",
	/*131*/ "Zerg Hatchery",
	/*132*/ "Zerg Lair",
	/*133*/ "Zerg Hive",
	/*134*/ "Zerg Nydus Canal",
	/*135*/ "Zerg Hydralisk Den",
	/*136*/ "Zerg Defiler Mound",
	/*137*/ "Zerg Greater Spire",
	/*138*/ "Zerg Queen's Nest",
	/*139*/ "Zerg Evolution Chamber",
	/*140*/ "Zerg Ultralisk Cavern",
	/*141*/ "Zerg Spire",
	/*142*/ "Zerg Spawning Pool",
	/*143*/ "Zerg Creep Colony",
	/*144*/ "Zerg Spore Colony",
	/*145*/ "Unused Zerg Bldg",
	/*146*/ "Zerg Sunken Colony",
	/*147*/ "Zerg Overmind (With Shell)",
	/*148*/ "Zerg Overmind",
	/*149*/ "Zerg Extractor",
	/*150*/ "Mature Crysalis",
	/*151*/ "Zerg Cerebrate",
	/*152*/ "Zerg Cerebrate Daggoth",
	/*153*/ "Unused Zerg Bldg 5",
	/*154*/ "Protoss Nexus",
	/*155*/ "Protoss Robotics Facility",
	/*156*/ "Protoss Pylon",
	/*157*/ "Protoss Assimilator",
	/*158*/ "Protoss Unused type 1",
	/*159*/ "Protoss Observatory",
	/*160*/ "Protoss Gateway",
	/*161*/ "Protoss Unused type 2",
	/*162*/ "Protoss Photon Cannon",
	/*163*/ "Protoss Citadel of Adun",
	/*164*/ "Protoss Cybernetics Core",
	/*165*/ "Protoss Templar Archives",
	/*166*/ "Protoss Forge",
	/*167*/ "Protoss Stargate",
	/*168*/ "Stasis Cell/Prison",
	/*169*/ "Protoss Fleet Beacon",
	/*170*/ "Protoss Arbiter Tribunal",
	/*171*/ "Protoss Robotics Support Bay",
	/*172*/ "Protoss Shield Battery",
	/*173*/ "Khaydarin Crystal Formation",
	/*174*/ "Protoss Temple",
	/*175*/ "Xel'Naga Temple",
	/*176*/ "Mineral Field (Type 1)",
	/*177*/ "Mineral Field (Type 2)",
	/*178*/ "Mineral Field (Type 3)",
	/*179*/ "Cave (Unused)",
	/*180*/ "Cave-in (Unused)",
	/*181*/ "Catina (Unused)",
	/*182*/ "Mining Platform",
	/*183*/ "Independent Command Center",
	/*184*/ "Independent Starport",
	/*185*/ "Jump Gate",
	/*186*/ "Ruins",
	/*187*/ "Kyadarin Crystal Formation",
	/*188*/ "Vespene Geyser",
	/*189*/ "Warp Gate",
	/*190*/ "Psi Disrupter",
	/*191*/ "Zerg Marker",
	/*192*/ "Terran Marker",
	/*193*/ "Protoss Marker",
	/*194*/ "Zerg Beacon",
	/*195*/ "Terran Beacon",
	/*196*/ "Protoss Beacon",
	/*197*/ "Zerg Flag Beacon",
	/*198*/ "Terran Flag Beacon",
	/*199*/ "Protoss Flag Beacon",
	/*200*/ "Power Generator",
	/*201*/ "Overmind Cocoon",
	/*202*/ "Dark Swarm",
	/*203*/ "Floor Missile Trap",
	/*204*/ "Floor Hatch (Unused)",
	/*205*/ "Left Upper Level Door",
	/*206*/ "Right Upper Level Door",
	/*207*/ "Left Pit Door",
	/*208*/ "Right Pit Door",
	/*209*/ "Floor Gun Trap",
	/*210*/ "Left Wall Missile Trap",
	/*211*/ "Left Wall Flame Trap",
	/*212*/ "Right Wall Missile Trap",
	/*213*/ "Right Wall Flame Trap",
	/*214*/ "Start Location",
	/*215*/ "Flag",
	/*216*/ "Young Chrysalis",
	/*217*/ "Psi Emitter",
	/*218*/ "Data Disc",
	/*219*/ "Khaydarin Crystal",
	/*220*/ "Mineral Chunk (Type 1)",
	/*221*/ "Mineral Chunk (Type 2)",
	/*222*/ "Vespene Orb (Protoss Type 1)",
	/*223*/ "Vespene Orb (Protoss Type 2)",
	/*224*/ "Vespene Sac (Zerg Type 1)",
	/*225*/ "Vespene Sac (Zerg Type 2)",
	/*226*/ "Vespene Tank (Terran Type 1)",
	/*227*/ "Vespene Tank (Terran Type 2)",
	/*228*/ "ID:228",
	/*229*/ "[any unit]",
	/*230*/ "[men]",
	/*231*/ "[buildings]",
	/*232*/ "[factories]",
};
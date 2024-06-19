DROP TABLE IF EXISTS terrain_phase_info;
CREATE TABLE terrain_phase_info(  
  Id INT(10) unsigned NOT NULL,
  TerrainSwapMap INT(10) unsigned NOT NULL,
  Comment VARCHAR(255),
  PRIMARY KEY (Id, TerrainSwapMap)
);

DROP TABLE IF EXISTS terrain_swap_defaults;
CREATE TABLE terrain_swap_defaults(  
  MapId INT(10) unsigned NOT NULL,
  TerrainSwapMap INT(10) unsigned NOT NULL,
  Comment VARCHAR(255),
  PRIMARY KEY (MapId, TerrainSwapMap)
);

DROP TABLE IF EXISTS terrain_worldmap;
CREATE TABLE terrain_worldmap(  
  TerrainSwapMap INT(10) unsigned NOT NULL,
  WorldMapArea INT(10) unsigned NOT NULL,
  Comment VARCHAR(255),
  PRIMARY KEY (TerrainSwapMap, WorldMapArea)
);

DELETE FROM `terrain_swap_defaults`;
INSERT INTO `terrain_swap_defaults` (`MapId`, `TerrainSwapMap`, `Comment`) VALUES 
(0, 736, 'Twilight Highlands - Dragonmaw Port'),
(0, 1066, 'Stormwind Gunship Pandaria Start'),
(1, 719, 'Mount Hyjal default terrain'),
(1, 1074, 'Orgrimmar Gunship Pandaria Start'),
(654, 638, 'Gilneas default terrain'),
(654, 655, 'Gilneas - Duskmist Shore broken'),
(870, 971, 'Jade Forest Alliance Starting Terrain'),
(870, 1076, 'Jade Forest Horde Starting Terrain'),
(870, 1061, 'Krasarang Wilds - Domination Point'),
(870, 1062, 'Krasarang Wilds - Lion\'s Landing'),
(655, 656, 'Gilneas - UnkName2'),
(648, 659, 'Lost Isles - UnkName'),
(648, 661, 'Lost Isles - UnkName2'),
(860, 975, 'Wandering Island - Turtle Hurted'),
(860, 976, 'Wandering Island - Turtle Healed'),
(1064, 1120, 'Thunder King Horde Hub'),
(1064, 1121, 'Thunder Island Alliance Hub');

DELETE FROM `terrain_worldmap`;
INSERT INTO `terrain_worldmap` (`TerrainSwapMap`, `WorldMapArea`, `Comment`) VALUES 
(638, 545, 'Gilneas'),
(655, 678, 'Gilneas_terrain1'),
(656, 679, 'Gilneas_terrain2'),
(719, 683, 'Hyjal_terrain1'),
(1061, 910, 'KrasarangHorde'),
(1062, 910, 'KrasarangAlliance');

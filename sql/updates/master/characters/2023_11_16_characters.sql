
DROP TABLE IF EXISTS character_rated_bg_stats;
CREATE TABLE character_rated_bg_stats (
  guid int(10) UNSIGNED NOT NULL,
  personalRating int(10) UNSIGNED NOT NULL,
  matchmakerRating int(10) UNSIGNED NOT NULL,
  seasonGames int(10) UNSIGNED NOT NULL,
  weekGames int(10) UNSIGNED NOT NULL,
  thisWeekWins int(10) UNSIGNED NOT NULL,
  prevWeekWins int(10) UNSIGNED NOT NULL,
  bestWeekRating int(10) UNSIGNED NOT NULL,
  bestSeasonRating int(10) UNSIGNED NOT NULL,
  PRIMARY KEY (guid),
  CONSTRAINT fk__character_rated_bg_stats__characters FOREIGN KEY (guid)
    REFERENCES characters (guid) ON DELETE CASCADE ON UPDATE RESTRICT
)
ENGINE = INNODB DEFAULT CHARSET = utf8 ROW_FORMAT = DYNAMIC;

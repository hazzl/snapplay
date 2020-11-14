START TRANSACTION;
CREATE TABLE IF NOT EXISTS config (
        conf VARCHAR(32) PRIMARY KEY,
	value VARCHAR(32) NOT NULL
);
CREATE TABLE IF NOT EXISTS categories (
        id SMALLINT UNSIGNED PRIMARY KEY,
        name VARCHAR(64) NOT NULL UNIQUE KEY
);
CREATE TABLE IF NOT EXISTS genres (
        id SMALLINT UNSIGNED PRIMARY KEY,
        name VARCHAR(64) NOT NULL UNIQUE KEY
);
CREATE TABLE IF NOT EXISTS artists (
        id SMALLINT UNSIGNED PRIMARY KEY,
        name text NOT NULL UNIQUE KEY
);
CREATE TABLE IF NOT EXISTS albums (
        id SMALLINT UNSIGNED PRIMARY KEY,
        category SMALLINT UNSIGNED REFERENCES categories(id),
        name VARCHAR(128),
        datetime DATE,
        lastplayed DATETIME
);
CREATE TABLE IF NOT EXISTS songs (
	id INTEGER UNSIGNED PRIMARY KEY,
        album SMALLINT UNSIGNED NOT NULL REFERENCES albums(id),
	trackno TINYINT UNSIGNED,
	name VARCHAR(128),
	path VARCHAR(4096) NOT NULL UNIQUE KEY,
	rating TINYINT UNSIGNED,
	timesplayed SMALLINT UNSIGNED,
	timesskipped SMALLINT UNSIGNED,
	lastplayed DATETIME,
        filectime DATETIME NOT NULL
);
CREATE TABLE IF NOT EXISTS song_artists (
        song_id INTEGER UNSIGNED NOT NULL REFERENCES songs(id),
        artist_id SMALLINT UNSIGNED NOT NULL REFERENCES artists(id),
        artist_type TINYINT UNSIGNED NOT NULL
);
CREATE TABLE IF NOT EXISTS song_genres (
        song_id INTEGER UNSIGNED REFERENCES songs(id),
        genre_id SMALLINT UNSIGNED REFERENCES genres(id)
);
COMMIT;

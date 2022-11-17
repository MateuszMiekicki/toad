CREATE TABLE "role"
(
    id   INT,
    role VARCHAR NOT NULL UNIQUE,

    PRIMARY KEY (id)
);

INSERT INTO "role"
VALUES (1, 'admin'),
       (2, 'owner'),
       (3, 'guest');

CREATE TABLE "user"
(
    id       INT,
    role_id  INT     NOT NULL,

    email    VARCHAR NOT NULL UNIQUE,
    password VARCHAR NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT role_fk
        FOREIGN KEY (role_id)
            REFERENCES "role" (id)
);

CREATE TABLE device
{
    id    INT,

    alias VARCHAR NOT NULL,
    short_description VARCHAR,

    PRIMARY KEY (id)
};

CREATE TABLE device_identifier
{
    id        INT,
    device_id INT NOT NULL

    mac_address VARCHAR NOT NULL,
    hash        VARCHAR NOT NULL UNIQUE

    PRIMARY KEY (id),
    CONSTRAINT device_id_fk
    FOREIGN KEY (device_id)
        REFERENCES "device" (id)
};
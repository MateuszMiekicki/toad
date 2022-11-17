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
create table dispatchers
(
    id         bigint not null
        primary key,
    email      varchar(255),
    first_name varchar(255),
    is_banned  boolean,
    last_name  varchar(255)
);
alter table dispatchers owner to postgres;

create table dispatcher_model_roles
(
    dispatcher_model_id bigint not null
        constraint fkl6n7cqxbveil99cwln12vjifk
            references dispatchers,
    roles               integer
);
alter table dispatcher_model_roles owner to postgres;

create table airports
(
    id   bigint not null
        primary key,
    name varchar(255),
    size integer,
    x    double precision,
    y    double precision
);
alter table airports owner to postgres;

create table flights
(
    id              bigint not null
        primary key,
    airport_id      bigint,
    dispatcher_id   bigint,
    plane_id        bigint,
    timestamp_end   bigint,
    timestamp_start bigint
);
alter table flights owner to postgres;

create table planes
(
    id                bigint not null
        primary key,
    broken_percentage integer,
    built_year        integer,
    min_airport_size  integer,
    name              varchar(255),
    pilot             varchar(255),
    speed             integer
);
alter table planes owner to postgres;


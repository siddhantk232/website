---
title: "The Ultimate Hasura Development Setup"
date: "2021-02-28"
description: "How I set up and use Hasura graphql engine for local development with pgadmin4 and pldebugger."
layout: layouts/post.njk
permalink: "/posts/{{ title | slug }}/"
canonical: "/posts/the-ultimate-hasura-development-setup"
cssclass: "post-container"
tags:
  - posts
  - docker
  - hasura
---

In this post, we will look at how I set up and use Hasura graphql engine for local
development with pgadmin4 and pldbgapi (pldebugger).

## TLDR;

- This setup uses [Hasura cli](https://hasura.io/docs/latest/graphql/core/hasura-cli/index.html) to generate postgres migrations and hasura metadata.
- For debugging and other administrative operations, this setup uses [pgAdmin4](https://www.pgadmin.org/) with [pldbgapi](https://github.com/soycacan/pldebugger).
- You can check this [sample project](https://github.com/siddhantk232/ultimate-hasura-dev-setup) to get a better idea.

## Hasura Cli setup

To create a fresh hasura project, run `hasura init`. This will create a folder with the name you provide. Inside this folder, it creates many subfolders for managing different components of your hasura server.

The project structure looks like this:

```
.
├── config.yaml                # main config file
├── metadata                   # hasura metadata
│   ├── actions.graphql
│   ├── actions.yaml
│   ├── allow_list.yaml
│   ├── cron_triggers.yaml
│   ├── functions.yaml
│   ├── query_collections.yaml
│   ├── remote_schemas.yaml
│   ├── tables.yaml
│   └── version.yaml
├── migrations                 # postgres migrations
└── seeds

3 directories, 10 files
```

> The default config assumes you are running the graphql-engine at port 8080. You can change this setting in `config.yml`.

## Hasura local server with docker-compose

To easily spin up many containers for postgres, hasura and pgadmin, I am using [docker-compose](docs.docker.com/compose/).

The `docker-compose.yml` file looks like this:

```yaml
version: "3.6"
services:
  db:
    build:
      context: .
      dockerfile: Dockerfile.postgres
    image: postgres:13
    restart: always
    volumes:
      - db_volume:/var/lib/postgresql/data
    environment:
      POSTGRES_USER: siddhant           # default postgres superuse
      POSTGRES_PASSWORD: passwd         # password for siddhant
      POSTGRES_DB: hasura_db
  hasura:
    image: hasura/graphql-engine:latest
    ports:
      - "8080:8080"                     # default port expected by hasura cli
    depends_on:
      - "db"
    restart: always
    environment:
      HASURA_GRAPHQL_DATABASE_URL: postgres://siddhant:passwd@db:5432/hasura_db
      ## enable the console served by server
      HASURA_GRAPHQL_ENABLE_CONSOLE: "true" # set to "false" to disable console
      ## enable debugging mode. It is recommended to disable this in production
      HASURA_GRAPHQL_DEV_MODE: "true"
      HASURA_GRAPHQL_ENABLED_LOG_TYPES: startup, http-log, webhook-log, websocket-log, query-log
      ## uncomment next line to set an admin secret
      # HASURA_GRAPHQL_ADMIN_SECRET: myadminsecretkey
  pgadmin:
    image: dpage/pgadmin4
    restart: always
    environment:
      PGADMIN_DEFAULT_EMAIL: test@test.com
      PGADMIN_DEFAULT_PASSWORD: passwd
    ports:
      - "9090:80"
    volumes:
      - pgadmin_volume:/var/lib/pgadmin
volumes:
  db_volume:
  pgadmin_volume:
```

#### Some important things in this docker-compose file:

1. Service `db` uses postgres:13 official docker image with a custom Dockerfile to build this image.
   This custom Dockerfile.postgres installs [pldebugger](https://github.com/soycacan/pldebugger) extension for debugging procedural code.
   The code for this Dockerfile.postgres looks like this:

   ```dockerfile
    FROM postgres:latest

    ENV PG_MAJOR 13
    ENV PG_FULL 13.1

    # Install the postgresql debugger
    RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    postgresql-$PG_MAJOR-pldebugger

    EXPOSE 5432

    ```
    To enable this extension you need to run `CREATE EXTENSION pldbgapi;` in your postgres instance.
  
2. Service `hasura` uses the [hasura-graphql-engine](https://hub.docker.com/r/hasura/graphql-engine) provided by Hasura.
We are also exposing port 8080 so that this server is accessible by our hasura cli's console server.

3. Serice `pgadmin` use the [dpage/pgadmin4](https://hub.docker.com/r/dpage/pgadmin4/) docker image.
To use pgadmin we are exposing port 80 as 9090 on our system.

## That's it :)

Now you can use this setup by running the command `docker-compose up -d` inside the project folder.
This command will start all three services for us to use.

To access the hasura, console run `hasura console` command inside the project file.
This command will start a hasura console server that will record all your actions and update the `migrations` and other folders accordingly.

To access pgadmin, you can go to `localhost:9090` on your browser.
You can log in with the email and password you set in the docker-compose file. Also, for debugging your procedural inside pgadmin, read the docs here https://www.pgadmin.org/docs/pgadmin4/latest/debugger.html

> Run `CREATE EXTENSION pldbgapi;` inside your postgres instance to enable the pldebugger extension.
```

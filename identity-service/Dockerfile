FROM alpine

RUN apk update
RUN apk add java-cacerts openjdk17-jdk openjdk17-jre dos2unix

ADD ../gradle /app/gradle
ADD ../gradlew /app/gradlew
ADD ../build.gradle /app/build.gradle
ADD ../src /app/src

RUN cd /app &&\
    dos2unix gradlew &&\
    chmod +x gradlew &&\
    ./gradlew bootJar

CMD ["java", "-jar", "/app/build/libs/app.jar"]
EXPOSE ${IDENTITY_SERVICE_PORT}
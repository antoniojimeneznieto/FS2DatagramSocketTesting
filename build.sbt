val scala3Version = "3.2.2"

lazy val root = project
  .in(file("."))
  .settings(
    name := "fs2udpsocket",
    version := "0.1.0-SNAPSHOT",

    scalaVersion := scala3Version,

    libraryDependencies += "org.scalameta" %% "munit" % "0.7.29" % Test,

    libraryDependencies += "co.fs2" %% "fs2-core" % "3.6.1",

    libraryDependencies += "co.fs2" %% "fs2-io" % "3.6.1",


    libraryDependencies += "org.typelevel" %% "cats-effect" % "3.3.9"

  )

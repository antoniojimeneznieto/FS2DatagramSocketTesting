import cats.effect.{IO, IOApp, ExitCode, Resource}
import cats.effect.std.Console
import cats.syntax.all.*

import com.comcast.ip4s._

import fs2.Chunk
import fs2.io.net.{Socket, SocketGroup, Network, Datagram}

import scala.concurrent.duration.*


object UdpClient extends IOApp.Simple {
  val serverAddress = SocketAddress(ip"127.0.0.1", port"8888")
  val message = Chunk.array("io_uring rocks :)".getBytes())
  val datagram = Datagram(serverAddress, message)

  override def run: IO[Unit] =
    Network[IO].datagramSocketGroup().use {socketGroup => 
        socketGroup.openDatagramSocket().use {socket => 
            for {
                _ <- Console[IO].println(s"Sending message to ${serverAddress.host}:${serverAddress.port}")
                _ <- socket.write(datagram)

            } yield ()
        }
    }
}

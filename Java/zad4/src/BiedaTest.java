import java.util.*;

public class BiedaTest {
    static int errorCount = 0;

    public static void main(String[] args) {
        var b = new BusLine();
        b.addBusLine("A", new Position2D(1, 1), new Position2D(3, 16));
        b.addLineSegment("A", new LineSegment(new Position2D(1, 1), new Position2D(1, 4)));
        b.addLineSegment("A", new LineSegment(new Position2D(1, 14), new Position2D(3, 16)));
        b.addLineSegment("A", new LineSegment(new Position2D(6, 12), new Position2D(1, 12)));
        b.addLineSegment("A", new LineSegment(new Position2D(6, 4), new Position2D(6, 12)));
        b.addLineSegment("A", new LineSegment(new Position2D(1, 12), new Position2D(1, 14)));
        b.addLineSegment("A", new LineSegment(new Position2D(1, 4), new Position2D(6, 4)));

        b.addBusLine("B", new Position2D(1, 16), new Position2D(3, 2));
        b.addLineSegment("B", new LineSegment(new Position2D(1, 16), new Position2D(3, 14)));
        b.addLineSegment("B", new LineSegment(new Position2D(3, 14), new Position2D(3, 2)));

        b.addBusLine("E", new Position2D(1, 6), new Position2D(11, 1));
        b.addLineSegment("E", new LineSegment(new Position2D(4, 6), new Position2D(9, 1)));
        b.addLineSegment("E", new LineSegment(new Position2D(1, 6), new Position2D(4, 6)));
        b.addLineSegment("E", new LineSegment(new Position2D(9, 1), new Position2D(11, 1)));

        /*
        {A=
        [LineSegment [firstPosition=Position2D [col=1, row=1], lastPosition=Position2D [col=1, row=4]],
        LineSegment [firstPosition=Position2D [col=1, row=14], lastPosition=Position2D [col=3, row=16]],
        LineSegment [firstPosition=Position2D [col=6, row=12], lastPosition=Position2D [col=1, row=12]],
        LineSegment [firstPosition=Position2D [col=6, row=4], lastPosition=Position2D [col=6, row=12]],
        LineSegment [firstPosition=Position2D [col=1, row=12], lastPosition=Position2D [col=1, row=14]],
        LineSegment [firstPosition=Position2D [col=1, row=4], lastPosition=Position2D [col=6, row=4]]],
        B=
        [LineSegment [firstPosition=Position2D [col=1, row=16], lastPosition=Position2D [col=3, row=14]],
         LineSegment [firstPosition=Position2D [col=3, row=14], lastPosition=Position2D [col=3, row=2]]],
         E=
         [LineSegment [firstPosition=Position2D [col=4, row=6], lastPosition=Position2D [col=9, row=1]],
          LineSegment [firstPosition=Position2D [col=1, row=6], lastPosition=Position2D [col=4, row=6]],
          LineSegment [firstPosition=Position2D [col=9, row=1], lastPosition=Position2D [col=11, row=1]]]}
*/
        b.findIntersections();
        b.getLines();
        b.getIntersectionPositions();
        b.getIntersectionsWithLines();
        b.getIntersectionOfLinesPair();


        if (errorCount == 0)
            System.out.println("all tests passed");
    }
}
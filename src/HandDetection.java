import org.opencv.core.*;
import org.opencv.highgui.HighGui;
import org.opencv.imgproc.Imgproc;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.videoio.VideoCapture;

public class HandDetection {

    static {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }

    public static void main(String[] args) {
        String handCascadePath = "D:/Git/hand_detect/data/fist.xml";
        CascadeClassifier handCascade = new CascadeClassifier(handCascadePath);
        VideoCapture capture = new VideoCapture(0);

        if (!capture.isOpened()) {
            System.out.println("Error: Failed to open camera.");
            return;
        }
        Mat frame = new Mat();
        Core.flip(frame, frame, 1);

        HighGui.namedWindow("Hand Detection", HighGui.WINDOW_AUTOSIZE);
        
        boolean shouldExit = false;

        while (!shouldExit) {
            if (!capture.read(frame)) {
                System.out.println("Error: Failed to capture frame.");
                break;
            }

            // Get the center position of the window
            int windowHeight = frame.rows();
            int windowWidth = frame.cols();
            double centerX = windowWidth / 2.0;
            double centerY = windowHeight / 2.0;

            // Perform hand detection
            Mat gray = new Mat();
            Imgproc.cvtColor(frame, gray, Imgproc.COLOR_BGR2GRAY);
            MatOfRect hands = new MatOfRect();
            handCascade.detectMultiScale(gray, hands, 1.1, 5, 0, new Size(30, 30), new Size());

//          handCascade.detectMultiScale(gray, hands, 1.1, 5, 0, new Size(40, 70), new Size());
            // Avoid too much hand on the camera

            Rect[] handsArray = hands.toArray();



            int n = handsArray.length;
            double max = 0;
            int x_new = 0;
            int y_new = 0;
            int w_x = 0;
            int h_y = 0;

            // Eliminating noise point (taking the farthest point to the center)
            for (Rect hand : handsArray) {
                double distance = (Math.abs(hand.x - centerX) * Math.abs(hand.x - centerX))
                        + (Math.abs(hand.y - centerY) * Math.abs(hand.y - centerY));
                if (distance > max) {
                    max = distance;
                    x_new = hand.x;
                    y_new = hand.y;
                    w_x = hand.width;
                    h_y = hand.height;
                }
            }

            // Display the last point after eliminating noise point
            Imgproc.rectangle(frame, new Point(x_new, y_new), new Point(x_new + w_x, y_new + h_y), new Scalar(0, 255, 0), 2);

            // Display the frame
            HighGui.imshow("Hand Detection", frame);

            // Exit the loop if 'q' is pressed
            int keyPressed = HighGui.waitKey(1);
            if (keyPressed == 'q' || keyPressed == 27) { // 27 is the ASCII code for the Esc key
                shouldExit = true;
            }
        }

        // Release resources
        capture.release();
        HighGui.destroyWindow("Hand Detection");
    }
}
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.awt.image.PixelGrabber;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

import javax.imageio.ImageIO;

public final class ImageToCArray {
	public static int globalWidth, globalHeight;

	/**
	 * Converts a java.awt.Image into an array of pixels
	 */
	public static int[] convertToPixels(Image img) {
		int width = img.getWidth(null);
		int height = img.getHeight(null);
		int[] pixel = new int[width * height];
		globalWidth = width;
		globalHeight = height;

		PixelGrabber pg = new PixelGrabber(img, 0, 0, width, height, pixel, 0, width);
		try {
			pg.grabPixels();
		} catch (InterruptedException e) {
			throw new IllegalStateException("Error: Interrupted Waiting for Pixels");
		}
		if ((pg.getStatus() & ImageObserver.ABORT) != 0) {
			throw new IllegalStateException("Error: Image Fetch Aborted");
		}
		return pixel;
	}

	public void main(String[] args) {
		if (args.length != 1) {
			System.out.println("Invalid number of arguments\n");
			System.out.println("Usage: java -cp . ImageToCArray <image path>");
			System.exit(-1);
		}

		String image = args[0];

		BufferedImage img = null;
		try {
			img = ImageIO.read(new File(image));
		} catch (IOException e) {
		}

		int[] array = convertToPixels(img);

		StringBuilder res = new StringBuilder();
		int size = globalWidth * globalHeight;
		res.append("static unsigned int[").append(size).append("] = {").append(array[0]);
		for (int i = 1; i < array.length; i++)
			res.append(", ").append(array[i]);
		res.append("};");

		PrintWriter writer;
		try {
			writer = new PrintWriter(image + ".h", "UTF-8");
			writer.write(res.toString());
			writer.close();
		} catch (FileNotFoundException | UnsupportedEncodingException e) {
			e.printStackTrace();
		}

	}
}

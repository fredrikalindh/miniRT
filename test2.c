PSUEDO CODE

rayTrace()
{
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			for (shape = shapes; shape != NULL; shape = shape->next)
				trace();
				put_pixel_in_image();
		}
	}
}

int main(int argc, char const *argv[]) {
	checkArg();
	getinfo(argv[1]);
	initContactWOS();
	createWindow();
	createImage();

	rayTrace();

	exitNfree();
	return 0;
}

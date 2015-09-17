glEnable(GL_TEXTURE_3D);

   unsigned char* noise_data = (unsigned char*) malloc(NOISE_3D_SIZE * NOISE_3D_SIZE * NOISE_3D_SIZE * 4);
   unsigned char* ptr = noise_data;

	for (int i = 0; i < NOISE_3D_SIZE; ++i)
	{
		for (int j = 0; j < NOISE_3D_SIZE; ++j)
		{
			for (int k = 0; k < NOISE_3D_SIZE; ++k, ptr += 4)
         {
            double noise = 0.0;

            for (int m = 0, n = 1; m < 2; ++m, n = 2 * n)
            {
               noise = noise + (Perlin::Noise(i * 0.1 * n, j * 0.1 * n, k * 0.1 * n) / n);
            }

            noise = sin(1.0 * (i * 0.1) +  1.0 * noise); 

            *(ptr + 0) = (unsigned char) (noise * 128.0);
            *(ptr + 1) = (unsigned char) (noise * 128.0);
            *(ptr + 2) = (unsigned char) (noise * 128.0);
            *(ptr + 3) = (unsigned char) 0;

         }
		}
	}

   glGenTextures(1, &g_perlin);
   glBindTexture(GL_TEXTURE_3D, g_perlin);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, NOISE_3D_SIZE, NOISE_3D_SIZE, NOISE_3D_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, noise_data);

   free(noise_data);

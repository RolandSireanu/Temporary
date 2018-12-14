from __future__ import print_function, division
from keras.datasets import mnist
from keras.layers import Input, Dense, Reshape, Flatten, Dropout
from keras.layers import BatchNormalization, Activation, ZeroPadding2D
from keras.layers.advanced_activations import LeakyReLU
from keras.layers.convolutional import UpSampling2D, Conv2D
from keras.models import Sequential, Model
from keras.optimizers import Adam
import matplotlib.pyplot as plt
import sys
import numpy as np
import ipdb 



class GAN():

    def __init__(self , rows , cols , channels):
        
        opt = Adam(0.0002 , 0.5)

        self.img_rows = rows;
        self.img_cols = cols;
        self.img_channels = channels;
        self.input_image_shape = (self.img_rows , self.img_cols , self.img_channels)
        self.latent_space_dimenstion = 100;

        self.gen = self.buildGenerator();
        self.gen.compile(loss="binary_crossentropy" , optimizer = opt , metrics=["accuracy"])

        self.disc = self.buildDiscriminator();
        self.disc.compile(loss="binary_crossentropy" , optimizer = opt);

        i = Input(shape=(100,))
        img = self.gen(i);

        self.disc.trainable = False;        
        valid = self.disc(img);

        self.combinedModel = Model(i , valid);
        self.combinedModel.compile(loss="binary_crossentropy" , optimizer = opt)




    def buildGenerator(self):
        
        noise_shape=(100,)
        sequentialModel = Sequential();
        noiseInput = Input(shape=(noise_shape))
        sequentialModel.add(Dense(units=256 , input_shape=noise_shape));
        sequentialModel.add(LeakyReLU(alpha=0.2))
        sequentialModel.add(BatchNormalization(momentum=0.8))
        sequentialModel.add(Dense(units=512));
        sequentialModel.add(LeakyReLU(alpha=0.2))
        sequentialModel.add(BatchNormalization(momentum=0.8))
        sequentialModel.add(Dense(units=1024));
        sequentialModel.add(LeakyReLU(alpha=0.2))
        sequentialModel.add(BatchNormalization(momentum=0.8))
        sequentialModel.add(Dense(np.prod(self.input_image_shape) , activation="tanh"))
        sequentialModel.add(Reshape(self.input_image_shape))
        sequentialModel.summary();

        outputTensor = sequentialModel(noiseInput);                

        return Model(noiseInput , outputTensor)


    def buildDiscriminator(self):

        sequentialModel = Sequential();

        inputLayer = Input(shape=(self.img_rows , self.img_cols , self.img_channels))

        sequentialModel.add(Flatten(input_shape=(self.img_rows , self.img_cols , self.img_channels)));
        sequentialModel.add(Dense(512));
        sequentialModel.add(LeakyReLU(alpha=0.2))
        sequentialModel.add(Dense(256));
        sequentialModel.add(LeakyReLU(alpha=0.2))
        sequentialModel.add(Dense(1 , activation="sigmoid"));
        sequentialModel.summary();

        valid = sequentialModel(inputLayer)

        print(type(valid))
        print(type(inputLayer))

        return Model(inputLayer , valid);

    def train(self , epochs , batch_size = 128 , save_interval = 50):
        
        #(X_train , _),(_,_) = mnist.load_data();        

        X_train = np.load("../AutoencodersTensorflow/x_train.npy");


        X_train = (X_train.astype(np.float32) - 127.5) / 127.5
        X_train = np.expand_dims(X_train , axis=3)


        half_batch = int(batch_size / 2)



        for e in range(epochs):
            index = np.random.randint(0 , X_train.shape[0] , half_batch);            
            images = X_train[index];

            noise = np.random.normal(0 , 1 , (half_batch , 100));
            print(noise.shape) 
            #Bullshits generated_images            
            generated_images = self.gen.predict(noise);

            real_loos = self.disc.train_on_batch(images , np.ones((half_batch , 1)))
            fake_loos = self.disc.train_on_batch(generated_images , np.zeros((half_batch , 1)))
            d_loss = 0.5 * np.add(real_loos , fake_loos)

            
            

            noise = np.random.normal(0,1,(batch_size , 100))

            #valid_y.shape = (32,) [1 ... 1]
            valid_y = np.array([1] * batch_size)
            g_loss = self.combinedModel.train_on_batch(noise, valid_y)

            # Plot the progress
            #print ("%d [D loss: %f, acc.: %.2f%%] [G loss: %f]" % (e, d_loss[0], 100*d_loss[1], g_loss))
            print("epoch = {} disc_loss = {} gen_loss = {}".format(e , d_loss,g_loss))

            # If at save interval => save generated image samples
            if e % save_interval == 0:
                self.save_imgs(e)

    def save_imgs(self, epoch):
        r, c = 5, 5
        noise = np.random.normal(0, 1, (r * c, 100))
        gen_imgs = self.gen.predict(noise)

        # Rescale images 0 - 1
        gen_imgs = 0.5 * gen_imgs + 0.5

        fig, axs = plt.subplots(r, c)
        cnt = 0
        for i in range(r):
            for j in range(c):
                axs[i,j].imshow(gen_imgs[cnt, :,:,0], cmap='gray')
                axs[i,j].axis('off')
                cnt += 1
        fig.savefig("mnist_%d.png" % epoch)
        plt.close()

GenerativeAdvNetwork = GAN(28,28,1);
GenerativeAdvNetwork.train(epochs=32000 , batch_size=32 , save_interval=200)


















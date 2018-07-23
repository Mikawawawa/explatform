# MQTT server
#
# VERSION  1.0.0

FROM datagovsg/python-node

RUN mkdir -p /home/mqtt
WORKDIR /home/mqtt

COPY . /home/mqtt
RUN npm install

EXPOSE 3000
CMD ["npm", "start"]

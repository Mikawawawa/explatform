apt remove nodejs -y
rm -rf /usr/local/bin/node /usr/local/bin/npm /usr/local/bin/npx
rm -rf /usr/local/lib/node_modules
mkdir pkg
wget https://nodejs.org/dist/v8.11.3/node-v8.11.3-linux-x64.tar.xz -P ./pkg -O ./pkg/node.tar.xz
xz -d ./pkg/node.tar.xz
mkdir /home/nodejs
tar -xvf ./pkg/node.tar -C /home/nodejs/
rm -rf pkg
mv /home/nodejs/node-v8.11.3-linux-x64 /home/nodejs/bin/
ln -s /home/nodejs/bin/bin/node /usr/local/bin/node
ln -s /home/nodejs/bin/bin/npm /usr/local/bin/npm
ln -s /home/nodejs/bin/bin/npx /usr/local/bin/npx
node -v

cd ../..
SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)

echo "cmd run at $SHELL_FOLDER"

docker pull mysql
docker run -d -e MYSQL_ROOT_PASSWORD=123456 --name mainDb -v $SHELL_FOLDER/data/mysql/data:/var/lib/mysql -v $SHELL_FOLDER/data/mysql/my.cnf:/etc/my.cnf -p 8101:3306 mysql
docker container ls
echo "\nNow,login the database via \n\tmysql -p\nThen exec this commond:\n\tALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'newpassword';\nEnjoy it!\n"

docker exec -it mainDb bash
/*
 * Simulated Device Driver © 2023 by Andrea Bonino, Gabriele Fasolis, Mattia
 * Mattiauda, Ettore Mondino, Federico Tartaglia is licensed under Attribution-
 * NonCommercial 4.0 International. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

#include <linux/err.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/sysfs.h>

#define REG_ID            0x0

#define REG_INIT        0x4
#define HW_ENABLE        BIT(0)

#define REG_CMD            0x8

#define REG_BUSY		0xc

#define REG_INT_STATUS        0x10
#define IRQ_ENABLED        BIT(0)
#define IRQ_INPUT              BIT(1)
#define IRQ_OUTPUT             BIT(2)

#define REG_INPUT		0x14
#define SIZE_INPUT		101

#define REG_OUTPUT		0x79
#define SIZE_OUTPUT		65

struct virt_sha {
    struct device *dev;
    void __iomem *base;
};


static ssize_t vf_show_id(struct device *dev,
              struct device_attribute *attr, char *buf)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
    u32 val = readl_relaxed(vf->base + REG_ID);
    return scnprintf(buf, PAGE_SIZE, "Chip ID: 0x%.x\n", val);
}


static ssize_t vf_show_cmd(struct device *dev,
               struct device_attribute *attr, char *buf)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
    u32 val = readl_relaxed(vf->base + REG_CMD);
    return scnprintf(buf, PAGE_SIZE, "Command buffer: 0x%.x\n", val);
}


static ssize_t vf_store_cmd(struct device *dev,
                struct device_attribute *attr,
                const char *buf, size_t len)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
    unsigned long val;

    if (kstrtoul(buf, 0, &val))
        return -EINVAL;

    writel_relaxed(val, vf->base + REG_CMD);
    return len;
}


static ssize_t vf_show_busy(struct device *dev,
               struct device_attribute *attr, char *buf)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
    u32 val = readl_relaxed(vf->base + REG_BUSY);
    return scnprintf(buf, PAGE_SIZE, "%.x\n", val);
}


static ssize_t vf_show_input(struct device *dev,
               struct device_attribute *attr, char *buf)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
	int i;
	char c;
	char input_driver[SIZE_INPUT];
	input_driver[0]='\0';
	i=0;

	while((input_driver[i]=ioread8(vf->base+REG_INPUT+i))!=0){
		i++;
	}
	input_driver[i]='\0';
	//printk(KERN_INFO "M fun: vf_show_input mex: input = %s\n",input_driver);

	return scnprintf(buf,SIZE_INPUT,"%s\n",input_driver);
}

static ssize_t vf_store_input(struct device *dev,
                struct device_attribute *attr,
                const char *buf, size_t len)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
    unsigned long val;
	int i;
//	writel_relaxed(1, vf->base + REG_BUSY);
	for(i=0;i<len-1;i++){
		iowrite8(buf[i],vf->base+REG_INPUT+i);
	}
	iowrite8('\0',vf->base+REG_INPUT+i);
	writel_relaxed(1, vf->base + REG_BUSY);

    return len;
}


static ssize_t vf_show_output(struct device *dev,
               struct device_attribute *attr, char *buf)
{
    struct virt_sha *vf = dev_get_drvdata(dev);
	int i;
	char output_driver[SIZE_OUTPUT];
	output_driver[0]='\0';
	i=0;
	while((output_driver[i]=ioread8(vf->base+REG_OUTPUT+i))!=0){
		i++;
	}
	output_driver[i]='\0';
	writel_relaxed(0,vf->base+REG_BUSY);

	//printk(KERN_INFO "M fun: vf_show_input stringa mex: output = %s\n",output_driver);
	return scnprintf(buf,SIZE_OUTPUT+1,"%s\n",output_driver);
	//return 1;
}


static DEVICE_ATTR(id, S_IRUGO, vf_show_id, NULL);
static DEVICE_ATTR(cmd, S_IRUGO | S_IWUSR, vf_show_cmd, vf_store_cmd);
static DEVICE_ATTR(input, S_IRUGO | S_IWUSR, vf_show_input, vf_store_input);
static DEVICE_ATTR(output, S_IRUGO, vf_show_output, NULL);
static DEVICE_ATTR(busy, S_IRUGO, vf_show_busy, NULL);


static struct attribute *vf_attributes[] = {
    &dev_attr_id.attr,
    &dev_attr_cmd.attr,
    &dev_attr_input.attr,
    &dev_attr_output.attr,
    &dev_attr_busy.attr,
    NULL,
};

static const struct attribute_group vf_attr_group = {
    .attrs = vf_attributes,
};

static void vf_init(struct virt_sha *vf)
{
    writel_relaxed(HW_ENABLE, vf->base + REG_INIT);
    printk(KERN_INFO "M fun: vf_init mex: write REG_INIT\n");

}

static irqreturn_t vf_irq_handler(int irq, void *data)
{
    struct virt_sha *vf = (struct virt_sha *)data;
    u32 status;

    status = readl_relaxed(vf->base + REG_INT_STATUS);

    if (status & IRQ_ENABLED)
        dev_info(vf->dev, "ISR: HW is enabled\n");

    if (status & IRQ_INPUT){}
//	dev_info(vf->dev, "ISR: Input inserito\n");

    if (status & IRQ_OUTPUT){}
//	dev_info(vf->dev, "ISR: Output pronto\n");

    return IRQ_HANDLED;
}

static int vf_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    struct resource *res;
    struct virt_sha *vf;
    int ret;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    printk(KERN_INFO "M fun: vf_probe mex: get_resource_MEM\n");
    printk(KERN_INFO "M fun: vf_probe mex: get_resource_MEM res.start=%p res.end=%p\n", res->start, res->end);

    if (!res)
        return -ENOMEM;

    vf = devm_kzalloc(dev, sizeof(*vf), GFP_KERNEL);
    printk(KERN_INFO "M fun: vf_probe mex: kzalloc\n");

    if (!vf)
        return -ENOMEM;

    vf->dev = dev;
    printk(KERN_INFO "M fun: vf_probe mex: copia dev\n");

    printk(KERN_INFO "M fun: vf_probe mex: before ioremap vf.base=%p\n", vf->base);
    vf->base = devm_ioremap(dev, res->start, resource_size(res));
    printk(KERN_INFO "M fun: vf_probe mex: io_remap\n");
    printk(KERN_INFO "M fun: vf_probe mex: ioremap vf.base=%p  vf_start=%p\n", vf->base, res->start);

    if (!vf->base)
        return -EINVAL;

    res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
    printk(KERN_INFO "M fun: vf_probe mex: get_resource_IRQ\n");

    if (res) {
        ret = devm_request_irq(dev, res->start, vf_irq_handler,
                       IRQF_TRIGGER_HIGH, "vf_irq", vf);
        if (ret)
            return ret;
    }

    platform_set_drvdata(pdev, vf);

    printk(KERN_INFO "M fun: vf_probe mex: before call vf_init\n");
    vf_init(vf);
    printk(KERN_INFO "M fun: vf_probe mex: after call vf_init\n");
    iowrite8(0,vf->base+REG_BUSY);


   return sysfs_create_group(&dev->kobj, &vf_attr_group);
}

static int vf_remove(struct platform_device *pdev)
{
    struct virt_sha *vf = platform_get_drvdata(pdev);

    sysfs_remove_group(&vf->dev->kobj, &vf_attr_group);
    return 0;
}

static const struct of_device_id vf_of_match[] = {
    { .compatible = "virt-sha-driver", },
    { }
};
MODULE_DEVICE_TABLE(of, vf_of_match);

static struct platform_driver vf_driver = {
    .probe = vf_probe,
    .remove = vf_remove,
    .driver = {
        .name = "virt-sha-drivername",
        .of_match_table = vf_of_match,
    },
};
module_platform_driver(vf_driver);

MODULE_DESCRIPTION("Virtual Sha Driver");
MODULE_AUTHOR("group10");
MODULE_LICENSE("GPL");

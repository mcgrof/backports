#ifndef __BACKPORT_LINUX_MDIO_H
#define __BACKPORT_LINUX_MDIO_H
#include_next <linux/mdio.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
/**
 * mmd_eee_adv_to_ethtool_adv_t
 * @eee_adv: value of the MMD EEE Advertisement/Link Partner Ability registers
 *
 * A small helper function that translates the MMD EEE Advertisment (7.60)
 * and MMD EEE Link Partner Ability (7.61) bits to ethtool advertisement
 * settings.
 */
#define mmd_eee_adv_to_ethtool_adv_t LINUX_BACKPORT(mmd_eee_adv_to_ethtool_adv_t)
static inline u32 mmd_eee_adv_to_ethtool_adv_t(u16 eee_adv)
{
	u32 adv = 0;

	if (eee_adv & MDIO_EEE_100TX)
		adv |= ADVERTISED_100baseT_Full;
	if (eee_adv & MDIO_EEE_1000T)
		adv |= ADVERTISED_1000baseT_Full;
	if (eee_adv & MDIO_EEE_10GT)
		adv |= ADVERTISED_10000baseT_Full;
	if (eee_adv & MDIO_EEE_1000KX)
		adv |= ADVERTISED_1000baseKX_Full;
	if (eee_adv & MDIO_EEE_10GKX4)
		adv |= ADVERTISED_10000baseKX4_Full;
	if (eee_adv & MDIO_EEE_10GKR)
		adv |= ADVERTISED_10000baseKR_Full;

	return adv;
}
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0) */

#endif /* __BACKPORT_LINUX_MDIO_H */
